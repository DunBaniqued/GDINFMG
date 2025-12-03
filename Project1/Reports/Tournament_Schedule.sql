SELECT
T.name "Tournament", 
L.name "Location", 
T.cash_prize_amount "Cash Prize", 
T.video_game_id "Video Game", 
T.start_date "Start Date", 
T.end_date "End Date"

FROM 
Tournaments T, 
Events E,
Locations L

WHERE 
T.event_id=E.id AND 
E.location_id=L.id
