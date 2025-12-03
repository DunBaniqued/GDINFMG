SELECT
CS.name "Match Corporate Sponsors"

FROM
Matches M,
Match_Advertisements MA,
Advertisements A,
Corporate_Sponsors CS

WHERE
CS.id=A.corporate_sponsor_id AND
A.id=MA.advertisement_id AND
MA.match_id=M.id
