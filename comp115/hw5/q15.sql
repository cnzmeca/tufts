select name
from member
except
select name
from member
where member_id in (
	select from_member_id
	from routing
)
