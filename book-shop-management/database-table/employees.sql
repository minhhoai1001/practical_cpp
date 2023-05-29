CREATE TABLE employees (
    id SERIAL,
    name  VARCHAR(50),
    addr_line1 VARCHAR(50),
    addr_line2 VARCHAR(50),
    addr_city VARCHAR(50),
    addr_state VARCHAR(50),
    phn BIGINT,
    date_of_joining DATE,
    salary BIGINT,
    mgr_status VARCHAR(1) DEFAULT 'F',
    PRIMARY KEY(id)
);