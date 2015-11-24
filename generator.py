import optparse
import re
from classwriter import ClassWriter

CToJavaTypeMapping = {
	"double" : "double",
	"char" : "char",
	"int" : "int",
	"char[]" : "String"
}

class FieldInfo:
	def __init__(self, fieldType, fieldName):
		self.fieldType = fieldType
		self.fieldName = fieldName

	def __str__(self):
		return self.fieldType + " " + self.fieldName

class StructInfo:
	def __init__(self, structName, fields):
		self.structName = structName
		self.fields = fields

	def __str__(self):
		return self.structName + "{\n" + '\n'.join(str(f) for f in self.fields) + "\n}"

def readDataType(filename):
	file = open(filename, 'r')
	lines = file.readlines()
	filtered = filter(hasTypedef, lines)
	return {k:CToJavaTypeMapping[v] for k,v in dict(map(getType, filtered)).iteritems()}

def hasTypedef(s):
	return "typedef" in s

def toJavaType(cType):
	return cType[0], CToJavaTypeMapping[cType[1]]

def getType(s):
	p = re.match("typedef ([^ ]*) ([^\[]*)(.*);", s)
	grouped = p.groups()
	if len(grouped) < 3:
		print "Error: Cannot parse type at " + s
	if grouped[0] == "char" and grouped[2] != "":
		return grouped[1], "char[]"
	else:
		return grouped[1], grouped[0]

def readDataStruct(filename):
	file = open(filename, 'r')
	content = file.read()
	pattern = re.compile(r"struct\s+[^;,{}]+\s*{.*?};", re.DOTALL)
	p = pattern.findall(content)
	return map(parseDataStruct, p)


#return StructInfo
def parseDataStruct(struct):
	pattern = re.compile(r"struct\s+([^;,{}]+)\s{(.*)}", re.DOTALL)
	m = re.match(pattern, struct)
	g = m.groups()
	return StructInfo(g[0], parseStructBody(g[1]))

def parseStructBody(body):
	pattern = re.compile(r"\w+\s+\w+;", re.DOTALL)
	p = pattern.findall(body)
	return map(parseField, p)

#return FieldInfo
def parseField(line):
	m = re.match(r"(\w+)\s+(\w+);", line)
	g = m.groups()
	f = FieldInfo(g[0], g[1])
	return FieldInfo(g[0], g[1])

if __name__ == "__main__":
	classWriter = ClassWriter("template/java.template")
	typeMapping = readDataType("USTPFtdcUserApiDataType.h")
	allStructs = readDataStruct("USTPFtdcUserApiStruct.h")
	for s in allStructs:
		classWriter.write(typeMapping, s, "com.ullink", "struct", True)


