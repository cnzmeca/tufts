select message_date
from message
where message_id in(
	select message_id
	from routing
	where from_member_id in (
		select member_id
		from member
		where name = 'Unguiferous'
	)
)
intersect
select message_date
from message 
where message_id in(
        select message_id
        from routing
        where from_member_id in (
                select member_id
                from member
                where name = 'Abderian'
        )
)
order by message_date
