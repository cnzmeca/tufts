select name, min(message_date), max(message_date)
from member full outer join routing on member_id = from_member_id
	full outer join message on routing.message_id = message.message_id
group by name
order by name
