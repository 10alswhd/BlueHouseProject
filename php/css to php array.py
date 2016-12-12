import cssutils
import urllib2

css_url = 'url_to_css_file.css'
css = urllib2.urlopen(css_url).read()

sheet = cssutils.parseString(css)

f = open("array.php", "w")
f.write('<?php\n')
f.write("$locationPositions = array(\n")

previousParentRule = ''
nextParentRule = ''
i = 0
for rule in sheet:
    rules = rule.selectorList.selectorText.split(' ')
    parentRule = rules[0].replace('.','')
    childRule = rules[1].replace('.','')
    
    if parentRule != previousParentRule:
        if i != 0:
            f.write("    ),\n")
        f.write("    '" + parentRule + "' => array(\n")
      
    f.write("        '" + childRule + "' => array(\n")  
    j = 0
    for property in rule.style:
        ruleslength = rule.style.length - 1
        writedown = "            '" + property.name + "' => '" + property.value.replace('%','') + "',"
        if j == ruleslength:
            writedown = writedown[:-1]
        f.write(writedown + "\n")
        j += 1
        
    f.write("        ),\n")
    
    previousParentRule = parentRule
    i += 1

f.write(");")

f.close()
