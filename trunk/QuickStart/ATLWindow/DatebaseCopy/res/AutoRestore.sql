declare @bkfile varchar(200)
set @bkfile = 'f:\net\OrchardDB_11171614274.bak'
declare @targetDbName varchar(200)
set @targetDbName = 'MyOrchardDb3'

--删除现有数据库
EXEC msdb.dbo.sp_delete_database_backuphistory @database_name = @targetDbName
USE [master]
IF  EXISTS (select * from master..SysDatabases where name = @targetDbName)
begin
	declare @dropSql varchar(200)
	set @dropSql = 'DROP DATABASE ['+ @targetDbName +']'
	exec(@dropSql)
end
--默认的数据库路径
declare @defaultPath varchar(200)
select @defaultPath = (select fileName from master..sysdatabases where name='master')
set @defaultPath = reverse(@defaultPath)
set @defaultPath=reverse(substring(@defaultPath,charindex('\',@defaultPath),260))
select @defaultPath

--存储临时文件信息表
create table #filelistinfo
(
	LogicalName	nvarchar(128) 	,
	PhysicalName	nvarchar(260) 	,
	[Type]	char(1) 	,
	FileGroupName	nvarchar(128) 	,
	Size	numeric(20,0) 	,
	MaxSize	numeric(20,0) 	,
	FileID	bigint 	,
	CreateLSN	numeric(25,0) 	,
	DropLSN	numeric(25,0) NULL	,
	UniqueID	uniqueidentifier 	,
	ReadOnlyLSN	numeric(25,0) NULL 	,
	ReadWriteLSN	numeric(25,0) NULL	,
	BackupSizeInBytes	bigint 	,
	SourceBlockSize	int 	,
	FileGroupID	int 	,
	LogGroupGUID	uniqueidentifier NULL 	,
	DifferentialBaseLSN	numeric(25,0) NULL	,
	DifferentialBaseGUID	uniqueidentifier 	,
	IsReadOnly	bit 	,
	IsPresent	bit 	,
	TDEThumbprint	varbinary(32)
)
--从备份文件中获取逻辑文件信息，得到@moveSql
declare @sql varchar(200)
set @sql = 'restore filelistonly from disk='''+@bkfile+''''
insert into #filelistinfo exec(@sql) 
select LogicalName,[Type] from #filelistinfo 
declare @moveSql varchar(1024)
set @moveSql = ''
declare @LogicalName varchar(128)
declare @Type char(1)
declare @index int
set @index=0 
declare #f cursor for select LogicalName,[Type] from #filelistinfo 
open #f 
fetch next from #f into @LogicalName,@Type

while @@fetch_status=0
	begin 
		set @moveSql=@moveSql+',move '''+@LogicalName+''' to '''+@defaultPath+@targetDbName+cast(@index as varchar) 
		+ case @Type when 'D' then '.mdf''' else '.ldf''' end 
		set @index=@index+1 
		fetch next from #f into @LogicalName,@Type 
	end 
close #f 
deallocate #f 
drop table #filelistinfo
print @moveSql

--还原数据库
declare @restoreSql varchar(1024)
set @restoreSql = 'restore database ' + @targetDbName + ' from disk=''' + @bkfile + '''WITH  FILE = 1' + @moveSql
--print @restoreSql
exec(@restoreSql)