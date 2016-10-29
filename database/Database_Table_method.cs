/// <summary>
    /// Returns the result Table of the specified SQL.
    /// </summary>
    /// <param name="sql">The SQL.</param>
    /// <param name="parameters">The parameters.</param>
    /// <param name="commandType">Type of the command.</param>
    /// <returns></returns>
    internal DataTable Table(string sql, dynamic parameters = null, CommandType? commandType = null) {
        DataTable table = new DataTable();

        using (SqlCommand command = new SqlCommand(sql, CreateConnection())) {
            if (commandType != null)
                command.CommandType = commandType.Value;

            IDictionary<string, string> parameterDictionary = parameters as IDictionary<string, string>;

            if (parameterDictionary != null)
                foreach (var parameter in parameterDictionary.Keys)
                    command.Parameters.AddWithValue("@" + parameter, parameterDictionary[parameter]);
            else
                if (parameters != null)
                    foreach (var property in parameters.GetType().GetProperties())
                        command.Parameters.AddWithValue("@" + property.Name, property.GetGetMethod().Invoke(parameters, null));

            using (SqlDataAdapter adapter = new SqlDataAdapter(command))
                adapter.Fill(table);

            return table;
        }
    }
