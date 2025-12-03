-- 1. Organizers
INSERT INTO Organizers (id, first_name, last_name) VALUES
(700, 'Alex', 'Tan'),
(701, 'Maria', 'Reyes'),
(702, 'John', 'Lim'),
(703, 'Sophia', 'Chan'),
(704, 'Ethan', 'Goh');

-- 2. Locations
INSERT INTO Locations (id, name, street_address, street, town, city, country) VALUES
(500, 'SMX Convention Center', '123 Seaside Ave', 'Seaside Blvd', 'Pasay', 'Manila', 'Philippines'),
(501, 'Waterfront Arena', '88 Lahug Road', 'Lahug St', 'Lahug', 'Cebu City', 'Philippines'),
(502, 'Davao Convention Hall', '15 Eco St', 'EcoLand Rd', 'Talomo', 'Davao City', 'Philippines'),
(503, 'Suntec Expo', '2 Temasek Blvd', 'Temasek Blvd', 'Central', 'Singapore', 'Singapore');

-- 3. Events
INSERT INTO Events (id, location_id, name, description, start_date, end_date, start_time, end_time) VALUES
(400, 500, 'Manila Esports Expo', 'Large gaming expo with tournaments', '2025-03-12', '2025-03-15', '10:00', '22:00'),
(401, 501, 'Cebu Gaming Festival', 'Regional esports festival', '2025-05-01', '2025-05-03', '09:00', '21:00'),
(402, 502, 'Davao Cyber Arena', 'LAN tournaments and live showcases', '2025-07-10', '2025-07-12', '08:00', '20:00'),
(403, 503, 'Singapore Esports Week', 'International esports gathering', '2025-09-03', '2025-09-06', '10:00', '23:00');

-- 4. Event_Organizers
INSERT INTO Event_Organizers (organizer_id, event_id) VALUES
(700, 400),
(701, 400),
(702, 401),
(703, 402),
(704, 403);

-- 5. Video_Games
INSERT INTO Video_Games (id, name, genre) VALUES
(300, 'Valorant', 'FPS'),
(301, 'Mobile Legends', 'MOBA'),
(302, 'Counter-Strike 2', 'FPS'),
(303, 'Tekken 7', 'Fighting'),
(304, 'Osu!', 'Rhythm');

-- 6. Tournaments
INSERT INTO Tournaments (id, event_id, video_game_id, name, description, start_date, end_date, start_time, end_time, cash_prize_amount) VALUES
(010, 400, 300, 'Valorant Pacific Cup', 'Tier-2 Regional Valorant Tournament', '2025-03-12', '2025-03-15', '11:00', '20:00', 12000),
(011, 401, 301, 'MLBB Visayas Clash', 'Mobile Legends regional championship', '2025-05-01', '2025-05-03', '10:00', '19:00', 15000),
(012, 403, 302, 'CS2 International Showdown', 'Global Counter-Strike event', '2025-09-03', '2025-09-06', '12:00', '21:00', 30000);

-- 7. Tournament_Organizers
INSERT INTO Tournament_Organizers (organizer_id, tournament_id) VALUES
(700, 010),
(701, 010),
(702, 011),
(703, 011),
(704, 012),
(700, 012);

-- 8. Teams
INSERT INTO Teams (id, name, type, country) VALUES
(900, 'Meta Horizon', 'Professional', 'Philippines'),
(901, 'Night Owls', 'Professional', 'Philippines'),
(902, 'Harpoon Fish', 'Professional', 'Singapore'),
(903, 'Team Mundo', 'Professional', 'Japan'),
(904, 'Orange Monarchs', 'Professional', 'Philippines'),
(905, 'Purple Shoguns', 'Professional', 'Malaysia'),
(906, 'Yellow Spartans', 'Professional', 'Philippines'),
(907, 'Red Turbans', 'Professional', 'Thailand'),
(908, 'Team Epic', 'Professional', 'Singapore');

-- 9. Players
INSERT INTO Players (id, team_id, first_name, last_name) VALUES
(800, 900, 'Kyle', 'Santos'),
(801, 900, 'Raven', 'Torres'),
(802, 900, 'Jake', 'Cruz'),
(803, 900, 'Leo', 'Gomez'),
(804, 901, 'Mark', 'Villanueva'),
(805, 901, 'Ian', 'Fernandez'),
(806, 901, 'Vince', 'Lopez'),
(807, 901, 'Adrian', 'Yu'),
(808, 902, 'Sean', 'Ocampo'),
(809, 902, 'Daniel', 'Uy'),
(810, 902, 'Patrick', 'Chua'),
(811, 902, 'Allen', 'Sison'),
(812, 903, 'Jiro', 'Tan'),
(813, 903, 'Rico', 'Mendoza'),
(814, 903, 'Zivv', 'Elomina'),
(815, 903, 'EJ', 'De Castro'),
(816, 904, 'Cedric', 'Mapili'),
(817, 904, 'Johann', 'Naranjo'),
(818, 904, 'Noel', 'Bautista'),
(819, 904, 'Yuri', 'Salazar'),
(820, 905, 'Lucas', 'Ang'),
(821, 905, 'Dun', 'Baniqued'),
(822, 905, 'Brett', 'Sarmiento'),
(823, 905, 'Jasper', 'Torralba'),
(824, 906, 'Owen', 'Rivera'),
(825, 906, 'Mike', 'Soriano'),
(826, 906, 'Chan', 'Park'),
(827, 906, 'Angeli', 'Fernandez'),
(828, 907, 'Zed', 'Navarro'),
(829, 907, 'Aiden', 'Flores'),
(830, 907, 'Ralph', 'Lee'),
(831, 907, 'Tristan', 'Yu'),
(832, 908, 'Bryan', 'Santos'),
(833, 908, 'Nate', 'Ong'),
(834, 908, 'Ethan', 'Go'),
(835, 908, 'Kyle', 'Naranjo');

-- 10. Matches
INSERT INTO Matches (id, tournament_id, team1_id, team2_id, winning_team_id, losing_team_id, next_match_id, cash_prize_amount, start_date, end_date, start_time, end_time, placement) VALUES
(600, 010, 900, 901, 900, 901, 601, 5000, '2025-03-12', '2025-03-12', '14:00', '15:00', 1),
(601, 010, 900, 902, 902, 900, NULL, 7000, '2025-03-13', '2025-03-13', '16:00', '17:00', 1),
(602, 011, 903, 904, 903, 904, 603, 6000, '2025-05-01', '2025-05-01', '11:00', '12:00', 1),
(603, 011, 903, 905, 905, 903, NULL, 8000, '2025-05-02', '2025-05-02', '13:00', '14:00', 1),
(604, 012, 906, 907, 907, 906, 605, 7500, '2025-09-03', '2025-09-03', '10:00', '11:00', 1),
(605, 012, 907, 908, 908, 907, NULL, 9000, '2025-09-04', '2025-09-04', '12:00', '13:00', 1);

-- 11. Match_Organizers
INSERT INTO Match_Organizers (organizer_id, match_id) VALUES
(700, 600),
(701, 601),
(703, 602),
(704, 603);

-- 12. Corporate_Sponsors
INSERT INTO Corporate_Sponsors (id, name) VALUES
(200, 'RedBull'),
(201, 'Logitech'),
(202, 'Intel'),
(203, 'Razer'),
(204, 'NVIDIA');

-- 13. Advertisements
INSERT INTO Advertisements (id, corporate_sponsor_id, name, format) VALUES
(100, 200, 'RedBull PowerPlay', 'Video'),
(101, 201, 'Logitech Gear Up', 'Banner'),
(102, 202, 'Intel Extreme', 'LED Screen'),
(103, 203, 'Razer Unleashed', 'Video'),
(104, 204, 'NVIDIA Reflex Ads', 'Banner');

-- 14. Match_Advertisements
INSERT INTO Match_Advertisements (match_id, advertisement_id) VALUES
(600, 100),
(600, 101), 
(601, 102), 
(602, 103), 
(603, 104);