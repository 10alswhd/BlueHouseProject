Form f = showForm("ExamDetails", null);
        f.setLayout(new BorderLayout());

        DefaultListModel<StringPair> model = new DefaultListModel<StringPair>(exam.getDetails().getDetails());
        List lst = new List(model);
        lst.setRenderer(new StringPairCellRenderer());
        f.addComponent(BorderLayout.CENTER, lst);
