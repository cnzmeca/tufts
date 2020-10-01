analyze r;
analyze s;
analyze t;
analyze u;

CREATE INDEX i on r(r_2);
explain select * from r where r_2 = 0;
DROP INDEX i;

CREATE INDEX i on r(r_1p);
explain select * from r where r_1p = 0;
DROP INDEX i;

CREATE INDEX i on r(r_50p);
explain select * from r where r_50p = 0;
DROP INDEX i;

/* These 3 queries received different query plans because the columns vary drastically in
selectivity. The first query used an index scan because there are only 2 entries that satisfy the
query, so using an index will find them very quickly. The second query used a bitmap heap scan
with a bitmap index scan, which queries heap pages and does and sequentially opens a short list
of pages and takes all rows that satisfy the condition. This plan is used because a simple index
scan would have poor spatial locality, while a sequential scan would open and close every page.
The third query used a sequential scan because so many of the rows in r satisfy the query that it
is most efficient to just check each one.*/

CREATE INDEX i on r(r_1p, r_10p, r_50p);
explain select * from r 
where r_1p = 0
and r_10p = 0
and r_50p = 0;
DROP INDEX i;

CREATE INDEX i on r(r_10p, r_50p, r_1p);
explain select * from r 
where r_1p between 0 and 5
and r_10p = 0
and r_50p = 0;
DROP INDEX i;

CREATE INDEX i_s on s(t_id);
CREATE INDEX i_s2 on s(u_id);
CREATE INDEX i_r on r(s_id);
CREATE INDEX i_u on u(u_5);
explain select t.*
from t
join s using (t_id)
join r using (s_id)
join u using (u_id)
where u_5 = 0;
DROP INDEX i_s;
DROP INDEX i_s2;
DROP INDEX i_r;
DROP INDEX i_u;

CREATE INDEX i_r on r(s_id);
CREATE INDEX i_s on s(s_4);
explain select r_10, s_20
from r
join s using (s_id)
where r_50p = 0
and s_4 = 0;
DROP INDEX i_r;
DROP INDEX i_s;

CREATE INDEX i on r(r_10);
CREATE INDEX i2 on r(r_1p);
explain select * 
from r
where r_1p = 0
or r_10 = 0;
DROP INDEX i;
DROP INDEX i2;

CREATE INDEX i_s on r(s_id);
CREATE INDEX i_t on s(t_id);
CREATE INDEX i_s2 on s(s_20);
CREATE INDEX i_t2 on t(t_5);
explain select *
from r
join s using (s_id)
join t using (t_id)
where s_20 = 0
and t_5 = 0;
DROP INDEX i_s;
DROP INDEX i_s2;
DROP INDEX i_t;
DROP INDEX i_t2;
