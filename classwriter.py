import os
import string
import io

class ClassWriter:
	def __init__(self, templatepath, spaceForPadding):
		self.scripttemplate = open(templatepath, 'r').read()
		self.padding = " " * 4 if spaceForPadding else "\t" * 4

	def write(self, typeMapping, structInfo, packageName, targetFolder, useGetter):
		targetFilePath = targetFolder + "/" + structInfo.structName + ".java"
		if not os.path.exists(os.path.dirname(targetFilePath)):
			os.makedirs(os.path.dirname(targetFilePath))
		targetFile = io.open(targetFilePath, 'w+', newline='\n')
		structFields = structInfo.fields
		fieldString = "".join(self.toJavaField(typeMapping, f) for f in structFields)
		constructorParams = ",\n{}".format(self.padding * 2).join(self.toConstuctorParameterField(typeMapping, f) for f in structFields)
		constuctorBody	= "\n{}".format(self.padding * 2).join(self.toConstuctorBody(typeMapping, f) for f in structFields)
		getters = "".join(self.toGetter(typeMapping, f) for f in structFields) if useGetter else ""
		classString = self.scripttemplate.replace("{packagename}", packageName).replace("{fields}", fieldString).replace("{classname}", structInfo.structName) \
						.replace("{params}", constructorParams).replace("{constructorbody}", constuctorBody).replace("{getters}", getters)

		targetFile.write(unicode(classString))
		targetFile.close()

	def toJavaField(self, typeMapping, field):
		return "{}public final {:<6} {};\n".format(self.padding, typeMapping[field.fieldType], self.toLower(field.fieldName))

	def toConstuctorParameterField(self, typeMapping, field):
		return typeMapping[field.fieldType] + " " + self.toLower(field.fieldName)

	def toConstuctorBody(self, typeMapping, field):
		return "this.%s = %s;" % (self.toLower(field.fieldName), self.toLower(field.fieldName))


	def toGetter(self, typeMapping, field):
		return """	
{0}public {1} get{2}()
{3}{{
{4}return {5};
{6}}}
			   """.format(self.padding, typeMapping[field.fieldType], self.toUpper(field.fieldName), self.padding, self.padding * 2, self.toLower(field.fieldName), self.padding)

	def toLower(self, s):
		return s[:1].lower() + s[1:] if s else ''

	def toUpper(self, s):
		return s[:1].upper() + s[1:] if s else ''
