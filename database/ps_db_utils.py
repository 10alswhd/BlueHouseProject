# To change this template, choose Tools | Templates
# and open the template in the editor.

from sqlalchemy import *
from sqlalchemy.orm import *
import os
import datetime

class PsDB(object):
    engine = None
    meta = None
    Session = None


    def __init__(self):
        self.connect()

    def connect(self):
        # NLS_LANG=AMERICAN_AMERICA.AL32UTF8
        if not "NLS_LANG" in os.environ.keys():
            os.environ["NLS_LANG"]="AMERICAN_AMERICA.AL32UTF8"

        if PsDB.engine is None:
            PsDB.engine = create_engine('oracle://PS:MyORACLEPassword@my.oracle.server:1521/PSPRODDB', echo=False)
        if PsDB.meta is None:
            PsDB.meta = MetaData()
            PsDB.meta.bind = PsDB.engine
        if PsDB.Session is None:
            PsDB.Session = sessionmaker(bind=PsDB.engine)

    def get_session(self):
        self.connect()
        return PsDB.Session()

    def reverse_table(self, table_name, pkfield='dcid'):
        self.connect()
        if table_name in PsSsis.meta.tables.keys():
            return PsDB.meta.tables[table_name]
        return Table(table_name, PsDB.meta, Column(pkfield, Integer, primary_key=True), autoload=True)

    def reverse_all_tables(self):
        self.connect()
        self.meta.reflect(bind=self.engine)

    def current_term_prefix(self):
        ''' Returns 21 for school year 2011-2012:
            which is (2011 mod 100) + 10
        '''
        right_now = datetime.datetime.now()
        curr_year = right_now.year
        curr_month = right_now.month
        if curr_month < 7:
            curr_year = curr_year - 1

        return str((curr_year % 100) + 10)
