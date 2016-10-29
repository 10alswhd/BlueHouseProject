using System;
    using System.Collections.Generic;
    using System.Data;
    using System.Data.SqlClient;
    using System.Linq;
    using System.Reflection;

    /// <summary>
    /// Data Helper methods.
    /// </summary>
    public static class DatabaseUtils
    {
        public static string FormatWith(this string input, params object[] stuff)
        {
            return string.Format(input, stuff);
        }
        
        /// <summary>
        /// Gets the parameters from object.
        /// </summary>
        /// <param name="obj">The object.</param>
        /// <returns>A list of sql parameters based on the object properties</returns>
        /// <exception cref="System.ApplicationException">Exception raised if no matching type found for a parameter</exception>
        public static IList<SqlParameter> GetParamsFromObject(object obj)
        {
            var sqlParams = new List<SqlParameter>();

            if (obj != null)
            {
                foreach (var prop in obj.GetType().GetProperties())
                {
                    var propType = prop.PropertyType;

                    // Check the see if the property type is nullable, if it is get the base type.
                    if (prop.PropertyType.GetGenericArguments().Length > 0 && prop.PropertyType.GetGenericTypeDefinition() == typeof(Nullable<>))
                    {
                        propType = prop.PropertyType.GetGenericArguments().First();
                    }

                    var sqltype = GetDBType(propType);

                    var value = prop.GetValue(obj, null);

                    sqlParams.Add(new SqlParameter("@{0}".FormatWith(prop.Name), sqltype) { Value = value });
                }
            }

            return sqlParams;
        }

        public static string GetStoredProcedureStringFromParams(
            string storedProcedure,
            IEnumerable<SqlParameter> parameters)
        {
            const string Template = "exec {0} {1}";

            var paramNames = parameters.Select(x => ":{0}".FormatWith(x.ParameterName));

            return Template.FormatWith(storedProcedure, string.Join(", ", paramNames));
        }

        /// <summary>
        /// Returns the properties of the object.
        /// </summary>
        /// <param name="obj">The object to get the value from.</param>
        /// <returns>
        /// The properties of the object.
        /// </returns>
        public static PropertyInfo[] GetProperties(object obj)
        {
            var parentType = obj.GetType();

            return parentType.GetProperties(BindingFlags.Instance | BindingFlags.Public);
        }

        /// <summary>
        /// Returns the properties of the object.
        /// </summary>
        /// <typeparam name="TAttribute">The type of the attribute.</typeparam>
        /// <param name="obj">The object to get the value from.</param>
        /// <returns>
        /// The properties of the object.
        /// </returns>
        public static IEnumerable<PropertyInfo> GetPropertiesWithAttribute<TAttribute>(object obj)
        {
            Type parentType = obj.GetType();

            return parentType.GetProperties(BindingFlags.Instance | BindingFlags.Public).Where(x => Attribute.IsDefined(x, typeof(TAttribute), true));
        }

        private static SqlDbType GetDBType(Type theType)
        {
            var p1 = new SqlParameter();
            var tc = System.ComponentModel.TypeDescriptor.GetConverter(p1.DbType);
            if (tc.CanConvertFrom(theType))
            {
                p1.DbType = (DbType)tc.ConvertFrom(theType.Name);
            }
            else
            {
                // Try brute force
                try
                {
                    p1.DbType = (DbType)tc.ConvertFrom(theType.Name);
                }
                catch (Exception ex)
                {
                    throw new ApplicationException(string.Format("Unable to auto map property type to SQL type: {0}", theType.FullName), ex);
                }
            }

            return p1.SqlDbType;
        }
