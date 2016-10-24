SELECT table_schema AS 'Database name',
	SUM(data_length + index_length) / 1024 / 1024 AS 'Size (MB)',
	SUM(data_free) / 1024 / 1024 AS 'Free (MB)'
FROM information_schema.TABLES
GROUP BY table_schema
