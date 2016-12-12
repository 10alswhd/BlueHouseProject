import base64
import sys
import re

SHELL = "<?php eval(base64_decode(\"{shell}\"));"
with open(sys.argv[1]) as f:
    source = f.readlines()

source = ''.join(source).replace('\n', '')
source = source.replace('<?php', '')
source = re.sub(' +',' ',source)
source = base64.b64encode(source)

print SHELL.format(shell=source)
