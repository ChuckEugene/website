PRAGMA foreign_keys = ON;

CREATE TABLE forms(
  id INTEGER PRIMARY KEY AUTOINCREMENT,
  file VARCHAR(250) NOT NULL,
  doctor VARCHAR(40) NOT NULL,
  created DATETIME DEFAULT CURRENT_TIMESTAMP,
  seen INTEGER DEFAULT 0
);

