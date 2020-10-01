-- Store in the routing table the rows (from_member_id, to_member_id, x), 
-- for each message id x in message_ids.
-- The return value should be the number of rows inserted.

create or replace function store_routing(
    from_member_id int, 
    to_member_id int, 
    message_ids int[]) returns int as $$
declare
    mid int;
    insert_count int;
begin
    insert_count := array_length(message_ids, 1);
    for mid in 1 .. insert_count loop
        insert into routing(from_member_id, to_member_id, message_id)
	values (from_member_id, to_member_id, message_ids[mid]);
    end loop;
    return insert_count;
end
$$ language plpgsql;
