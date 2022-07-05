import xml.etree.ElementTree as ET
tree = ET.parse('./HWCorso/HWCorso.xml')
root = tree.getroot()
components = root[1]

for c in components:
    print(c.attrib)