select name
from member 
where member_id in (
	select distinct from_member_id
	from routing
	where message_id in (
		select message_id
		from message
		where message_date = '2016/05/17'
	)
)
