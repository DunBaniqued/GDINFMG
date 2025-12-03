SELECT
A.name "Match Advertisement",
A.format "Advertisement Format"

FROM
Matches M,
Match_Advertisements MA,
Advertisements A

WHERE
A.id=MA.advertisement_id AND
MA.match_id=M.id
