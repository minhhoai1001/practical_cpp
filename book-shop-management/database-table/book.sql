CREATE TABLE books (
   id SERIAL PRIMARY KEY,
   name  VARCHAR(50),
   auth VARCHAR(50),
   price NUMERIC,
   qty INTEGER
);