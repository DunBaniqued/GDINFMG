SELECT
M.placement "Placement",
M.next_match_id "Next Match ID",
(
  SELECT
  name

  FROM
  Teams T,
  Matches M

  WHERE 
  M.losing_team_id = T.id
) "Losing Team",
(
  SELECT
  name

  FROM
  Teams T,
  Matches M

  WHERE 
  M.winning_team_id = T.id
) "Winning Team"

FROM 
Matches M
