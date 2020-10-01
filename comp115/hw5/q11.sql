select count(distinct message_id)
from routing
where to_member_id in (
	select member_id
	from member
	where name = 'Abderian'
)
	
