select distinct from_name, to_name
from (
	select name as from_name, routing.message_id
	from member join routing on member_id = from_member_id
	where message_id in (
		select message_id
		from message
		where message_date = '2016/05/17'
	)
) as f join (
	select name as to_name, routing.message_id
        from member join routing on member_id = to_member_id
        where message_id in (
                select message_id
                from message
                where message_date = '2016/05/17'
        )
) as t on f.message_id = t.message_id
order by from_name, to_name
