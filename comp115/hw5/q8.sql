select distinct name, count(name)
from (
	select to_member_id
	from member join routing on member_id = from_member_id
	where name = 'Lucarne' and to_member_id != from_member_id
) as f join member on to_member_id = member_id
group by name
order by count(name) desc
