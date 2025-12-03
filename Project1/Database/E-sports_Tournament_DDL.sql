CREATE TABLE Organizers (
  id INTEGER NOT NULL,
  first_name VARCHAR(31) NOT NULL,
  last_name VARCHAR(31) NOT NULL,
  PRIMARY KEY (id)
);

CREATE TABLE Locations (
  id INTEGER NOT NULL,
  name VARCHAR(31) NOT NULL,
  street_address VARCHAR(31),
  street VARCHAR(31),
  town VARCHAR(31),
  city VARCHAR(31),
  country VARCHAR(31),
  PRIMARY KEY (id)
);

CREATE TABLE Events (
  id INTEGER NOT NULL,
  location_id INTEGER,
  name VARCHAR(31) NOT NULL,
  description VARCHAR(401),
  start_date date NOT NULL,
  end_date date,
  start_time time NOT NULL,
  end_time time,
  PRIMARY KEY (id),
  FOREIGN KEY (location_id) REFERENCES Locations (id)
);

CREATE TABLE Event_Organizers (
  organizer_id INTEGER NOT NULL,
  event_id INTEGER NOT NULL,
  FOREIGN KEY (organizer_id) REFERENCES Organizers (id) ON DELETE CASCADE,
  FOREIGN KEY (event_id) REFERENCES Events (id) ON DELETE CASCADE
);

CREATE TABLE Video_Games (
  id INTEGER NOT NULL,
  name VARCHAR(51) NOT NULL,
  genre VARCHAR(31),
  PRIMARY KEY (id)
);

CREATE TABLE Tournaments (
  id INTEGER NOT NULL,
  event_id INTEGER,
  video_game_id INTEGER,
  name VARCHAR(31),
  description VARCHAR(401),
  start_date date,
  end_date date,
  start_time time,
  end_time time,
  cash_prize_amount INTEGER,
  PRIMARY KEY (id),
  FOREIGN KEY (event_id) REFERENCES Events (id) ON DELETE CASCADE,
  FOREIGN KEY (video_game_id) REFERENCES Video_Games (id) ON DELETE SET NULL
);

CREATE TABLE Tournament_Organizers (
  organizer_id INTEGER NOT NULL,
  tournament_id INTEGER NOT NULL,
  Foreign Key (organizer_id) REFERENCES Organizers (id) ON DELETE CASCADE,
  Foreign Key (tournament_id) REFERENCES Tournaments (id) ON DELETE CASCADE
);

CREATE TABLE Teams (
  id INTEGER NOT NULL,
  name VARCHAR(51) NOT NULL,
  type VARCHAR(31),
  country VARCHAR(31),
  PRIMARY KEY (id)
);

CREATE TABLE Players (
  id INTEGER NOT NULL,
  team_id INTEGER,
  first_name VARCHAR(31) NOT NULL,
  last_name VARCHAR(31) NOT NULL,
  PRIMARY KEY (id),
  FOREIGN KEY (team_id) REFERENCES Teams (id) ON DELETE SET NULL
);

CREATE TABLE Matches (
  id INTEGER NOT NULL,
  tournament_id INTEGER NOT NULL,
  team1_id INTEGER,
  team2_id INTEGER,
  winning_team_id INTEGER,
  losing_team_id INTEGER,
  next_match_id INTEGER,
  cash_prize_amount INTEGER,
  start_date date NOT NULL,
  end_date date,
  start_time time NOT NULL,
  end_time time,
  placement VARCHAR(31),
  PRIMARY KEY (id),
  FOREIGN KEY (tournament_id) REFERENCES Tournaments (id) ON DELETE CASCADE,
  FOREIGN KEY (team1_id) REFERENCES Teams (id) ON DELETE SET NULL,
  FOREIGN KEY (team2_id) REFERENCES Teams (id) ON DELETE SET NULL,
  FOREIGN KEY (winning_team_id) REFERENCES Teams (id) ON DELETE SET NULL,
  FOREIGN KEY (losing_team_id) REFERENCES Teams (id) ON DELETE SET NULL,
  FOREIGN KEY (next_match_id) REFERENCES Matches (id) ON DELETE SET NULL
);

CREATE TABLE Match_Organizers (
  organizer_id INTEGER NOT NULL,
  match_id INTEGER NOT NULL,
  Foreign Key (organizer_id) REFERENCES Organizers (id) ON DELETE CASCADE,
  Foreign Key (match_id) REFERENCES Matches (id) ON DELETE CASCADE
);

CREATE TABLE Corporate_Sponsors (
  id INTEGER NOT NULL,
  name VARCHAR(31) NOT NULL,
  PRIMARY KEY (id)
);

CREATE TABLE Advertisements (
  id INTEGER NOT NULL,
  corporate_sponsor_id INTEGER NOT NULL,
  name VARCHAR(31) NOT NULL,
  format VARCHAR(31) NOT NULL,
  PRIMARY KEY (id),
  FOREIGN KEY (corporate_sponsor_id) REFERENCES Corporate_Sponsors (id) ON DELETE CASCADE
);

CREATE TABLE Match_Advertisements (
  match_id INTEGER NOT NULL,
  advertisement_id INTEGER NOT NULL,
  Foreign Key (match_id) REFERENCES Matches (id) ON DELETE CASCADE,
  Foreign Key (advertisement_id) REFERENCES Advertisements (id) ON DELETE CASCADE
);

