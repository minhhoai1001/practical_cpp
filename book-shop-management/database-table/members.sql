CREATE TABLE members (
    id SERIAL,
    name  VARCHAR(50),
    addr_line1 VARCHAR(50),
    addr_line2 VARCHAR(50),
    addr_city VARCHAR(50),
    addr_state VARCHAR(50),
    phn BIGINT,
    beg_date DATE,
    end_date DATE,
    valid VARCHAR(10),
    PRIMARY KEY(id)
);