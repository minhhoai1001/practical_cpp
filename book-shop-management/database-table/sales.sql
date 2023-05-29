CREATE TABLE sales (
    invoice_id SERIAL,
    member_id INTEGER,
    book_id INTEGER,
    qty INTEGER,
    amount INTEGER,
    date_s DATE,
    PRIMARY KEY(invoice_id),
    CONSTRAINT fk_member FOREIGN KEY(member_id) REFERENCES members(id),
    CONSTRAINT fk_books FOREIGN KEY(book_id) REFERENCES books(id)
);