package jrails;

import java.io.*;
import java.util.*;
import java.lang.reflect.*;

public class Model {
    private Integer num = new Integer(0);

    public void save() {
        HashMap<Integer, Model> map = read();
    
        if (num.intValue() == 0) {
            Integer max_id = new Integer(0);
            for (Integer i: map.keySet()) {
                if (i.intValue() > max_id.intValue()) {
                    max_id = i;
                }
            }

            Integer new_id = new Integer(max_id.intValue() + 1);
            num = new_id;
        }
       
        map.put(num, this);
        write(map);
    }

    public int id() {
        return num.intValue();
    }
    
    public static <T> T find(Class<T> c, int id) {
        HashMap<Integer, Model> map = read();
        Model m = map.get(new Integer(id));
        return c.cast(m);
    }

    public static <T> List<T> all(Class<T> c) {
        HashMap<Integer, Model> map = read();
        List ret = new ArrayList<T>();
        for(HashMap.Entry<Integer, Model> entry : map.entrySet()) {
            try {
                ret.add(c.cast(entry.getValue()));
            } catch (ClassCastException e) {
            }
        }
        return ret; 
    }

    public void destroy() {
        HashMap<Integer, Model> map = read();
        if (map.remove(num) == null) {
            throw new RuntimeException();
        }
        //num = new Integer(0);
        write(map);
    }

    public static void reset() {
        write(new HashMap<Integer, Model>());
    }

    private static HashMap<Integer, Model> read() {
        HashMap<Integer, Model> map = new HashMap<Integer, Model>();
        File f = new File("db.tsv");
        try {
            if(!f.createNewFile()) {
                Scanner reader = new Scanner(f);
                while (reader.hasNextLine()) {
                    String line = reader.nextLine();
                    String[] data = line.split("\t");
                    Integer key = Integer.valueOf(data[0]);
                    Class c = Class.forName(data[1]);
                    Model val = (Model)c.newInstance();
                    val.num = key;
                    int i = 2;
                    for(Field field: c.getDeclaredFields())
                    {
                        if (field.isAnnotationPresent(Column.class))
                        {       
                            Class type = field.getType();
                            if (type == String.class) {
                                if (data[i] == "null") {
                                    field.set(val, null);
                                } else {
                                    field.set(val, data[i]);
                                }
                            } else if (type == int.class) {
                                field.set(val, Integer.parseInt(data[i]));
                            } else if (type == boolean.class) {
                                field.set(val, Boolean.parseBoolean(data[i]));
                            } else {
                                throw new RuntimeException();
                            }
                        }
                        i++;
                    }
                    map.put(key, val);
                }
                reader.close();
            }
        } catch (Exception e) {
            throw new RuntimeException(e);
        }
        return map; 
    }

    private static void write(HashMap<Integer, Model> map)
    {
        try {
            FileWriter writer = new FileWriter("db.tsv");
            for (HashMap.Entry<Integer, Model> entry : map.entrySet()) {
                Integer key = entry.getKey();
                Model val = entry.getValue();
                Class c = val.getClass();
                
                String line = key.toString() + "\t" + c.getName() + "\t";
                
                for(Field field: c.getDeclaredFields())
                {
                    if (field.isAnnotationPresent(Column.class))
                    {
                        line = line + field.get(val) + "\t";
                    }
                } 

                writer.write(line + "\n");
            }
            writer.close();
        } catch (Exception e) {
            throw new RuntimeException(e);
        }
    }
}
