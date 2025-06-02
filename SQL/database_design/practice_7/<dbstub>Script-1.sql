
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


INSERT INTO position (position_id, name, description, base_salary) VALUES
(1, 'Механик', 'Отвечает за техническое обслуживание', 50000),
(2, 'Инженер', 'Проводит осмотр и диагностику', 70000),
(3, 'Менеджер', 'Организует процессы на трассе', 60000);

INSERT INTO employee (employee_id, last_name, first_name, middle_name, position_id, salary) VALUES
(1, 'Иванов', 'Алексей', 'Петрович', 1, 52000),
(2, 'Сидорова', 'Марина', 'Игоревна', 2, 71000),
(3, 'Петров', 'Илья', 'Алексеевич', 3, 61000);

INSERT INTO pilot (pilot_id, last_name, first_name, middle_name, phone) VALUES
(1, 'Кузнецов', 'Дмитрий', 'Сергеевич', '89991234567'),
(2, 'Орлова', 'Анна', 'Михайловна', '89993456789');

INSERT INTO cards (card_id, card_model, card_state) VALUES
(1, 'Sodi RT8', 'Готов'),
(2, 'CRG Road Rebel', 'В ремонте');

INSERT INTO inspection (inspection_id, card_id, employee_id, date, status) VALUES
(1, 1, 1, '2025-05-01', 'Пройдено'),
(2, 2, 2, '2025-05-02', 'Требует ремонта');

INSERT INTO chat (chat_id, pilot_id, employee_id) VALUES
(1, 1, 1),
(2, 2, 3);

INSERT INTO message (chat_id, text, time, sender) VALUES
(1, 'Здравствуйте, когда будет следующая проверка?', '2025-05-03', 'pilot'),
(1, 'В пятницу утром. Будьте готовы.', '2025-05-03', 'employee'),
(2, 'У меня проблема с картом', '2025-05-04', 'pilot');

INSERT INTO track (track, name, city) VALUES
(1, 'Sochi Autodrom', 'Сочи'),
(2, 'Kazan Ring', 'Казань');

INSERT INTO race (race_id, date, time, track_id) VALUES
(1, '2025-06-10', '10:00:00', 1),
(2, '2025-06-15', '12:00:00', 2);

INSERT INTO participation (participation_id, pilot_id, card_id, place) VALUES
(1, 1, 1, 1),
(2, 2, 2, 2);

INSERT INTO participation_race (participation_race_id, participation_id, race_id) VALUES
(1, 1, 1),
(2, 2, 2);

INSERT INTO pilot_participation (pilot_id, participation_id) VALUES
(1, 1),
(2, 2);
