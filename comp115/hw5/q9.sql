select name, count(distinct routing.message_id)
from member join routing on member.member_id = routing.from_member_id
group by name
having count(distinct message_id) > 20
order by count(routing.message_id) desc
