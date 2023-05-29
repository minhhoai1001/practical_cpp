CREATE TABLE suppliers (
   id SERIAL,
   name  VARCHAR(50),
   phn BIGINT,
   addr_line1 VARCHAR(50),
   addr_line2 VARCHAR(50),
   addr_city VARCHAR(50),
   addr_state VARCHAR(50),
   PRIMARY KEY(id)
);