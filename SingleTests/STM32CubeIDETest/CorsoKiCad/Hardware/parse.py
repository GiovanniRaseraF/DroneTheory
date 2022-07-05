import xml.etree.ElementTree as ET
tree = ET.parse('./HWCorso/HWCorso.xml')
root = tree.getroot()
components = root[1]

print("Designator, Comment, Footprint, LCSC")

for c in components:
    # Designator
    print('"' + c.attrib["ref"] + '", ', end="")
    # Comment
    comment = c.find("value").text
    print('"' + comment + '", ', end="")
    # Footprint
    footp = c.find("footprint").text  
    print('"' + footp + '", ', end="")
    # LCSC
    lcsc = c.find("property").attrib["value"]
    print('"' + lcsc + '"', end="")   

    # end
    print()