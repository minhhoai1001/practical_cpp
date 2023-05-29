CREATE TABLE purchases (
    ord_id SERIAL,
    book_id INTEGER,
    sup_id INTEGER,
    qty INTEGER,
    dt_ordered DATE,
    eta INTEGER,
    received VARCHAR(1) DEFAULT 'F',
    inv INTEGER,
    PRIMARY KEY(ord_id),
    CONSTRAINT fk_suppliers FOREIGN KEY(sup_id) REFERENCES suppliers(id),
    CONSTRAINT fk_books FOREIGN KEY(book_id) REFERENCES books(id)
);