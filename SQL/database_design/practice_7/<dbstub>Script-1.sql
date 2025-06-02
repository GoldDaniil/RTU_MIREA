
DROP TABLE IF EXISTS pilot_participation CASCADE;
DROP TABLE IF EXISTS participation_race CASCADE;
DROP TABLE IF EXISTS participation CASCADE;
DROP TABLE IF EXISTS race CASCADE;
DROP TABLE IF EXISTS track CASCADE;
DROP TABLE IF EXISTS message CASCADE;
DROP TABLE IF EXISTS chat CASCADE;
DROP TABLE IF EXISTS inspection CASCADE;
DROP TABLE IF EXISTS cards CASCADE;
DROP TABLE IF EXISTS pilot CASCADE;
DROP TABLE IF EXISTS employee CASCADE;
DROP TABLE IF EXISTS position CASCADE;


CREATE TABLE position (
  position_id  integer NOT NULL PRIMARY KEY,
  name varchar(500) NOT NULL,
  description text,
  base_salary decimal
);

CREATE TABLE employee (
  employee_id integer NOT NULL PRIMARY KEY,
  last_name varchar(500) NOT NULL,
  first_name varchar(500) NOT NULL,
  middle_name varchar(500),
  position_id integer,
  salary decimal
);

CREATE TABLE pilot (
  pilot_id integer NOT NULL PRIMARY KEY,
  last_name varchar(500),
  first_name varchar(500),
  middle_name varchar(500),
  phone varchar(500)
);

CREATE TABLE cards (
  card_id integer NOT NULL PRIMARY KEY,
  card_model varchar(500) NOT NULL,
  card_state varchar(500) NOT NULL
);

CREATE TABLE inspection (
  inspection_id integer NOT NULL PRIMARY KEY,
  card_id integer,
  employee_id integer,
  date date NOT NULL,
  status varchar(500)
);

CREATE TABLE chat (
  chat_id integer NOT NULL PRIMARY KEY,
  pilot_id integer,
  employee_id integer
);

CREATE TABLE message (
  message_id serial NOT NULL PRIMARY KEY,
  chat_id integer NOT NULL,
  text text NOT NULL,
  time date NOT NULL,
  sender text NOT NULL
);

CREATE TABLE track (
  track integer NOT NULL PRIMARY KEY,
  name varchar(500) NOT NULL,
  city varchar(500)
);

CREATE TABLE race (
  race_id integer NOT NULL PRIMARY KEY,
  date date NOT NULL,
  time time NOT NULL,
  track_id integer
);

CREATE TABLE participation (
  participation_id integer NOT NULL PRIMARY KEY,
  pilot_id integer NOT NULL,
  card_id integer NOT NULL,
  place integer NOT NULL
);

CREATE TABLE participation_race (
  participation_race_id integer NOT NULL PRIMARY KEY,
  participation_id integer NOT NULL,
  race_id integer
);

CREATE TABLE pilot_participation (
  participation_pilot_id serial NOT NULL PRIMARY KEY,
  pilot_id integer NOT NULL,
  participation_id integer NOT NULL
);

ALTER TABLE employee
ADD CONSTRAINT fk_employee_position FOREIGN KEY (position_id)
REFERENCES position(position_id);

ALTER TABLE chat
ADD CONSTRAINT fk_chat_pilot FOREIGN KEY (pilot_id)
REFERENCES pilot(pilot_id);

ALTER TABLE chat
ADD CONSTRAINT fk_chat_employee FOREIGN KEY (employee_id)
REFERENCES employee(employee_id);

ALTER TABLE message
ADD CONSTRAINT fk_message_chat FOREIGN KEY (chat_id)
REFERENCES chat(chat_id);

ALTER TABLE inspection
ADD CONSTRAINT fk_inspection_card FOREIGN KEY (card_id)
REFERENCES cards(card_id);

ALTER TABLE inspection
ADD CONSTRAINT fk_inspection_employee FOREIGN KEY (employee_id)
REFERENCES employee(employee_id);

ALTER TABLE participation
ADD CONSTRAINT fk_participation_pilot FOREIGN KEY (pilot_id)
REFERENCES pilot(pilot_id);

ALTER TABLE participation
ADD CONSTRAINT fk_participation_card FOREIGN KEY (card_id)
REFERENCES cards(card_id);

ALTER TABLE race
ADD CONSTRAINT fk_race_track FOREIGN KEY (track_id)
REFERENCES track(track);

ALTER TABLE participation_race
ADD CONSTRAINT fk_pr_participation FOREIGN KEY (participation_id)
REFERENCES participation(participation_id);

ALTER TABLE participation_race
ADD CONSTRAINT fk_pr_race FOREIGN KEY (race_id)
REFERENCES race(race_id);

ALTER TABLE pilot_participation
ADD CONSTRAINT fk_pp_pilot FOREIGN KEY (pilot_id)
REFERENCES pilot(pilot_id);

ALTER TABLE pilot_participation
DROP CONSTRAINT IF EXISTS fk_pp_participation;

ALTER TABLE pilot_participation
ADD CONSTRAINT fk_pp_participation FOREIGN KEY (participation_id)
REFERENCES participation(participation_id);

