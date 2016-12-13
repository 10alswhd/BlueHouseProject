<前略>
  :
    for (i=1; i<size; i++) {
        if (debug) printf("table[%"PRIdSIZE"]: position: %d, line: %d, pos: %"PRIdSIZE"\n",
                  i, table[i].position, table[i].line_no, pos);

        if (table[i].position == pos) {
        return &table[i];
        }
        if (table[i].position > pos) {
        return &table[i-1];
        }
    }
    }
    return &table[i-1];
}   // get_line_info()ここまで
