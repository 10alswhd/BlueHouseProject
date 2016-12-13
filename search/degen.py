# -*- coding:utf-8 -*-

import TlvCodec

structList = TlvCodec.parse('src.txt')

output = ""


template = """%s
{
    int ptr=0;
    int ret=0;
    unsigned short iei, ielen;
    while (ptr < len)
    {
        iei = GETWORD(buf+ptr);
        ptr += 2;
        ielen = GETWORD(buf+ptr);
        ptr += 2;
        switch (iei)
        {
        %s
        default:
            DBGprintf("%s_decode: unknow IEI type\r\n");
            break;
        }
        ptr += ielen;
    }
    return ptr;
}
"""

declaration = "int %s_decode(struct %s *para, unsigned char *buf, int len, unsigned char *errmsg)"


def member_decode_gen(mem, structName):
    caseBuf = """case %s:
        %s
    break;
    """
    if mem.isStruct == True:
        callBuf = 'ret = %s_decode(para->%s, buf+ptr, ielen, errmsg)' % (mem.struct_name, mem.name) 
    else:
        callBuf = 'current pass'
    return caseBuf % (mem.iei, callBuf)


def struct_decode_gen(struct):
    caseBuf = ''
    for mem in struct.members:
        caseBuf += member_decode_gen(mem, struct.name)
    output = (template % (declaration, caseBuf, struct.name)) % (struct.name, struct.name)

    return output

for struct in structList:
    output += (declaration+';\n') % (struct.name, struct.name)

output += '\n\n\n'
print '============'

for struct in structList:
    output += struct_decode_gen(struct)

print output
Raw
 generated.c
int ewlan_ac_t_decode(struct ewlan_ac_t *para, unsigned char *buf, int len, unsi
gned char *errmsg);
int ewlan_ac_signal_t_decode(struct ewlan_ac_signal_t *para, unsigned char *buf,
 int len, unsigned char *errmsg);

int ewlan_ac_t_decode(struct ewlan_ac_t *para, unsigned char *buf, int len, unsi
gned char *errmsg)
{
    int ptr=0;
    int ret=0;
    unsigned short iei, ielen;

    while (ptr < len)
    {
        iei = GETWORD(buf+ptr);
        ptr += 2;
        ielen = GETWORD(buf+ptr);
        ptr += 2;

        switch (iei)
        {
        case EWLAN_AC_ID:
        current pass
    break;
    case EWLAN_AC_NAME:
        current pass
    break;
    case EWLAN_AC_COMPANY:
        current pass
    break;
    case EWLAN_AC_SWC_CTRL:
        current pass
    break;
    case EWLAN_AC_SIGNAL:
        ret = ewlan_ac_signal_t_decode(para->signal, buf+ptr, ielen, errmsg)
    break;

        default:
            DBGprintf("ewlan_ac_t_decode: unknow IEI type
");
            break;
        }

        ptr += ielen;
    }
    return ptr;
}

int ewlan_ac_signal_t_decode(struct ewlan_ac_signal_t *para, unsigned char *buf,
 int len, unsigned char *errmsg)
{
    int ptr=0;
    int ret=0;
    unsigned short iei, ielen;

    while (ptr < len)
    {
        iei = GETWORD(buf+ptr);
        ptr += 2;
        ielen = GETWORD(buf+ptr);
        ptr += 2;

        switch (iei)
        {
        case EWLAN_SIGNAL_NAME:
        current pass
    break;
    case EWLAN_SIGNAL_MAC:
        current pass
    break;

        default:
            DBGprintf("ewlan_ac_signal_t_decode: unknow IEI type
");
            break;
        }

        ptr += ielen;
    }
    return ptr;
}
Raw
 src.txt
struct ewlan_ac_t
{
    int flag NaV;
    int id  EWLAN_AC_ID constrain [0, 800];
    char name[64]  EWLAN_AC_NAME;
    char company[32]  EWLAN_AC_COMPANY;
    char swc_control[64]  EWLAN_AC_SWC_CTRL;
    struct ewlan_ac_signal_t signal[EWLAN_MAX_SIGNALS] EWLAN_AC_SIGNAL;
};

struct ewlan_ac_signal_t
{
    unsigned char signal_name[16]  EWLAN_SIGNAL_NAME;
    unsigned char signal_mac_addr[16]  EWLAN_SIGNAL_MAC;
};
Raw
 TlvCodec.py
# !/usr/bin/python
# -*- coding:utf-8 -*-
from time import sleep
import re

type_key_words = ['char', 'int', 'BYTE', 'WORD', 'float', 'double']
type_key_decorator = ['unsigned']


class Identity(object):

    def __init__(self, adict):

        super(Identity, self).__init__()
        self.name = adict['name']
        self.length = adict['length']
        self.isStruct = adict['isStruct']
        # dict, contains upper/lower flag, upper/lower bound
        # bound open/closed
        self.constraint = adict['constraint']
        # str
        self.iei = adict['iei']
        self.isNecessary = adict['isNecessary']
        if adict['subIdentity']:
            self.subIdentity = adict['subIdentity']


class Member(object):
    """docstring for Member"""
    def __init__(self, memStr):
        super(Member, self).__init__()
        self.isStruct = False
        self.memStr = memStr
        self.get_type()
        self.get_member_name()
        # print self.type, self.name
        if self.memStr.startswith('['):
            self.get_array_size()
        self.get_identifier_element()
        while self.memStr:
            self.get_attributes()

    def get_type(self):
        frags = self.memStr.split(' ')
        frags = list_trim(frags, '')
        # print frags
        if 'NaV' in frags:
            print 'Not a Valid Variable'
            raise Exception
        if frags[0] in type_key_words:
            self.type = frags[0]
            self.memStr = ' '.join(frags[1:]).strip(' ')
        elif frags[0] in type_key_decorator:
            if frags[1] in type_key_words:
                self.type = frags[1]
                self.decorator = frags[0]
                self.memStr = ' '.join(frags[2:]).strip(' ')
            else:
                print 'no valid member type'
                raise Exception
        elif frags[0] == 'struct':
            self.struct_name = frags[1]
            self.isStruct = True
            self.memStr = ' '.join(frags[2:]).strip(' ')

    def get_member_name(self):
        namePattern = re.compile(r'^(\w+)\W*')
        self.name = namePattern.search(self.memStr).groups()[0]
        self.memStr = self.memStr.lstrip(self.name).lstrip(' ')

    def get_array_size(self):
        self.size = self.memStr[1: self.memStr.index(']')].strip(' ')
        mark = self.memStr.index(']') + 1
        self.memStr = self.memStr[mark:].strip(' ')

    def get_identifier_element(self):
        iePattern = re.compile(r'^(\w+)\W*')
        self.iei = iePattern.search(self.memStr).groups()[0]
        self.memStr = self.memStr.lstrip(self.iei).strip(' ')

    def get_attributes(self):
        attrPattern = re.compile(r'^(\w+)\W*')
        try:
            attr = attrPattern.search(self.memStr).groups()[0]
        except:
            print 'no valid attribute string found'
            raise Exception
        self.memStr = self.memStr.lstrip(attr).strip(' ')
        if attr == 'constrain':
            self.get_constrain()
        elif attr == 'NaM':
            self.NaM = True
        elif attr == 'todo':
            self.todo = True
        elif attr == 'cbfunc':
            self.get_cbfunc()
        else:
            print 'unsupported member attribute'
            raise Exception

    def get_constrain(self):
        boundPattern = re.compile(r'^(\w+)\W*')
        delimiterPattern = re.compile(r'^(\W+)\w*')
        if self.memStr[0] == '(':
            self.lBoundType = 1
        elif self.memStr[0] == '[':
            self.lBoundType = 2
        else:
            print 'not a valid constrain', self.memStr[0]
            raise Exception

        self.memStr = self.memStr[1:].lstrip(' ')
        try:
            self.lBound = boundPattern.search(self.memStr).groups()[0]
        except:
            print 'invalid bound'
            raise Exception

        self.memStr = self.memStr.lstrip(self.lBound)
        delimiter = delimiterPattern.search(self.memStr).groups()[0]
        self.memStr = self.memStr.lstrip(delimiter).strip(' ')
        try:
            self.rBound = boundPattern.search(self.memStr).groups()[0]
        except:
            print 'not a valid rbound', self.memStr
            raise Exception

        self.memStr = self.memStr.lstrip(self.rBound).strip(' ')
        if self.memStr[0] == ')':
            self.rBoundType = 1
        elif self.memStr[0] == ']':
            self.rBoundType = 2
        else:
            print 'invalid rbound type', self.memStr[0]
            raise Exception

        self.memStr = self.memStr[1:].strip(' ')

    def get_cbfunc(self):
        funcNamePattern = re.compile(r'^(\w+)\W*')
        try:
            self.cbFuncName = funcNamePattern.search(self.memStr)
        except:
            print 'invaild callback function name', self.memStr
            raise Exception
        self.memStr = self.memStr.lstrip(funcNamePattern).strip(' ')

    def printInfo(self):
        print self.name


class Struct(object):
        """docstring for Struct"""
        def __init__(self, name, members):
            super(Struct, self).__init__()
            self.name = name
            self.members = members


class ParseError(Exception):
    def __init__(self):
        pass


def list_trim(srcl, trimed):
    return [item for item in srcl if item != trimed]


def str_trim(src, trimed):
    return ''.join([c for c in src if c != trimed])


def comment_proc(src):
    return src


def breakline_proc(src):
    return src


def prepare(content):
    # preparing
    content = comment_proc(content)
    content = breakline_proc(content)

    contentList = content.replace('\n', ' ')

    return contentList

struct_list = []


def identity_gen(struct_strs):
    print struct_strs


def get_one_struct(line):
    if not line.startswith('struct'):
        print 'line not start with struct'
        raise Exception
    try:
        rightBrace = line.index('}')
    except:
        print 'no } in line'
        raise Exception

    try:
        endSemi = line[rightBrace:].index(';') + rightBrace
    except:
        print 'no ; after }'
        raise Exception

    structBuf = line[:endSemi]
    try:
        remainBuf = line[endSemi + line[endSemi:].index('struct'):]
    except:
        remainBuf = ''

    return structBuf, remainBuf


def process_one_struct(words):
    try:
        head = words[:words.index('{')]
    except:
        print 'no { in this structure, error'
        raise Exception

    try:
        struct_name = list_trim(head.split(' '), '')[1]
    except:
        print 'struct_name error'

    body = words.lstrip(head)
    body = body[body.index('{')+1:]
    body = body[:body.index('}')]

    lines = body.strip(' ').split(';')
    lines = list_trim(lines, '')

    memlist = []
    for line in lines:
        try:
            mem = Member(line)
            memlist.append(mem)
        except:
            print 'passed one line', line

    return Struct(struct_name, memlist)


def parse(filename):
    f = open(filename)
    content = f.read()
    f.close()

    line = prepare(content)

    structList = []
    while True:
        try:
            structBuf, line = get_one_struct(line)
        except:
            break

        try:
            struct = process_one_struct(structBuf)
        except:
            print 'process struct fail', structBuf
            raise Exception
        structList.append(struct)
        if line == '':
            break

    return structList

if __name__ == '__main__':
    for struct in parse('./src.txt'):
        print 'Struct %s:' % struct.name
        for mem in struct.members:
            mem.printInfo()
        print '\n'
