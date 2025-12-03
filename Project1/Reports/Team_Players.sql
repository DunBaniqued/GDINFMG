SELECT
T.name "Team",
P.first_name "First Name",
P.last_name "Last Name"

FROM 
Players P,
Teams T

WHERE 
P.team_id=T.id