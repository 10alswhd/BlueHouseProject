SELECT table_schema "Database", 
       SUM(data_length + index_length) / 1024 / 1024  AS "Size in MB" 
FROM information_schema.TABLES
GROUP BY table_schema;
