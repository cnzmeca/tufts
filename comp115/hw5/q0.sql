select name
from member
except
select distinct name
from member
where member_id in (
	select from_member_id
	from routing
	where from_member_id = to_member_id
)
order by name
