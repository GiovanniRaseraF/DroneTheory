## Author: Giovanni Rasera
## Git: https://github.com/GiovanniRaseraF

import xml.etree.ElementTree as ET
import sys

tree = ET.parse(sys.argv[1])
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