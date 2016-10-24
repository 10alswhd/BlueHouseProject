DECLARE @backUpPath varchar(max) = 'D:\SQL\Backup\DBName-old.bak'
DECLARE @oldDbName varchar(max) = 'DBName-old'
DECLARE @newDbName varchar(max) = 'DBName-new'
DECLARE @sqlDataPath varchar(max) = 'D:\sql\data'

----------------------Create Backup-----------------------------------
BACKUP DATABASE @oldDbName TO DISK = @backUpPath
WITH
	INIT,
	COMPRESSION

----------------------Get Logical Name--------------------------------
-- Used to retrieve MDF/LDF Logical File Names

RESTORE FILELISTONLY
FROM DISK = @backUpPath

----------------------Restore Database with new name------------------
-- Populate the @mdfLogicalName/@ldfLogicalName variables with the names retrieved above

DECLARE @mdfLogicalName varchar(max) = 'DBName'
DECLARE @ldfLogicalName varchar(max) = 'DBName_log'
DECLARE @mdfFilePath varchar(max) = @sqlDataPath + @newDbName + '.mdf'
DECLARE @logFilePath varchar(max) = @sqlDataPath + @newDbName + '_1.ldf'

RESTORE DATABASE @newDbName
FROM DISK = @backUpPath
WITH MOVE @mdfLogicalName TO @mdfFilePath,
MOVE @ldfLogicalName TO @logFilePath
