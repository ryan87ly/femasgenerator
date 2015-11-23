import os

class ClassWriter:
	def __init__(self, templatepath):
		self.scripttemplate = open(templatepath, 'r').read()

	def write(self, typeMapping, structInfo, packageName, targetFolder):
		targetFilePath = targetFolder + "/" + structInfo.structName + ".java"
		if not os.path.exists(os.path.dirname(targetFilePath)):
			os.makedirs(os.path.dirname(targetFilePath))
		targetFile = open(targetFilePath, 'w+')
		structFields = structInfo.fields
		fieldString = "\n\t".join(self.toJavaField(typeMapping, f) for f in structFields)
		constructorParams = "\n\t\t".join(self.toConstuctorParameterField(typeMapping, f) for f in structFields)
		constuctorBody	= "\n\t\t".join(self.toConstuctorBody(typeMapping, f) for f in structFields)
		classString = self.scripttemplate.replace("{packagename}", packageName).replace("{fields}", fieldString).replace("{classname}", structInfo.structName) \
						.replace("{params}", constructorParams).replace("{constructorbody}", constuctorBody)
		targetFile.write(classString)

	def toJavaField(self, typeMapping, field):
		return "public final " + typeMapping[field.fieldType] + " " + self.toLower(field.fieldName) + ";"

	def toConstuctorParameterField(self, typeMapping, field):
		return typeMapping[field.fieldType] + " " + self.toLower(field.fieldName)

	def toConstuctorBody(self, typeMapping, field):
		return "this." + self.toLower(field.fieldName) + " = " + self.toLower(field.fieldName) + ";"

	def toLower(self, s):
		return s[:1].lower() + s[1:] if s else ''