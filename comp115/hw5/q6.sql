select name
from member
where member_id in (
	select to_member_id
	from routing
	where from_member_id in (
		select member_id
		from member
		where name = 'Cephalophore'
	)
)
order by name
