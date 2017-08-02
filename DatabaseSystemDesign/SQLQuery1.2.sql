USE dbs
GO
CREATE TABLE dbo.Product (
	maker char(10) NOT NULL, 
	model int NOT NULL,
	type char(10) NOT NULL
)
GO
CREATE TABLE dbo.PC (
	model int NOT NULL,
	speed float NOT NULL,
	ram int NOT NULL,
	hd int NOT NULL,
	price int NOT NULL
)
GO
CREATE TABLE dbo.Laptop (
	model int NOT NULL,
	speed float NOT NULL,
	ram int NOT NULL,
	hd int NOT NULL,
	screen float NOT NULL,
	price int NOT NULL
)
GO
CREATE TABLE dbo.Printer (
	model int NOT NULL,
	color char(10) NOT NULL,
	type char(10) NOT NULL,
	price int NOT NULL
)
GO