select name
from member
where member_id in (
	select to_member_id
	from routing
	where message_id in (
		select message_id
		from message
		where extract(month from message_date) = extract(month from birth_date)
		and extract(day from message_date) = extract(day from birth_date)
	)
)
order by name
