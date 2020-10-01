import java.util.*;
import java.lang.reflect.*;
import java.lang.annotation.*;

public class Unit {
    public static HashMap<String, Throwable> testClass(String name) {
        Class<?> c;
        try {
            c = Class.forName(name);
        } catch (ClassNotFoundException e) {
            return null;
        }   
    
        Object o;
        try {
            o = c.newInstance();
        } catch (InstantiationException | IllegalAccessException e) {
            return null;
        } 
        
        Method[] methods = c.getDeclaredMethods();

        Arrays.sort(methods, new Comparator<Method>() {
            @Override
            public int compare(Method m1, Method m2) {
                return m1.getName().compareTo(m2.getName());
            }
        });

        ArrayList<Method> bcm = new ArrayList<Method>();
        ArrayList<Method> bm = new ArrayList<Method>();
        ArrayList<Method> tm = new ArrayList<Method>();
        ArrayList<Method> am = new ArrayList<Method>();
        ArrayList<Method> acm = new ArrayList<Method>();
            
        for (Method m: methods) { 
            int i = 0;
            if (m.getAnnotation(BeforeClass.class) != null) {
                bcm.add(m);
                i++;
            }
            if (m.getAnnotation(Before.class) != null) {
                bm.add(m);
                i++;
            }
            if (m.getAnnotation(Test.class) != null) {
                tm.add(m);
                i++;
            }
            if (m.getAnnotation(After.class) != null) {
                am.add(m);
                i++;
            }
            if (m.getAnnotation(AfterClass.class) != null) {
                acm.add(m);
                i++;
            }

            if (i > 1) {
                throw new RuntimeException();
            }
        }


        HashMap<String, Throwable> ret = new HashMap<String, Throwable>();

        for (Method m: bcm) {
            try {
                m.invoke(null);
            } catch (IllegalAccessException | InvocationTargetException e){
                throw new RuntimeException();
            }
        }

        for (Method m: tm) {
            for (Method m2: bm) {
                try {
                    m2.invoke(o);
                } catch (IllegalAccessException | InvocationTargetException e){
                    throw new RuntimeException();
                }
            }
            try {
                m.invoke(o);
                ret.put(m.getName(), null);
            } catch (IllegalAccessException | InvocationTargetException e){
                ret.put(m.getName(), e.getCause());
            }
            for (Method m2: am) {
                try {
                    m2.invoke(o);
                } catch (IllegalAccessException | InvocationTargetException e){
                    throw new RuntimeException();
                }
            }
        }

        for (Method m: acm) {
            try {
                m.invoke(null);
            } catch (IllegalAccessException | InvocationTargetException e){
                throw new RuntimeException();
            }
        }

        return ret;
    }

    public static HashMap<String, Object[]> quickCheckClass(String name) {
        Class<?> c;
        try { 
            c = Class.forName(name);
        } catch (ClassNotFoundException e) {
            return null;
        }

        Object o;
        try { 
            o = c.newInstance();
        } catch (InstantiationException | IllegalAccessException e) {
            return null;
        }

        Method[] methods = c.getDeclaredMethods();

        Arrays.sort(methods, new Comparator<Method>() {
            @Override
            public int compare(Method m1, Method m2) {
                return m1.getName().compareTo(m2.getName());
            }
        });

        ArrayList<Method> pm = new ArrayList<Method>();
        for (Method m: methods) {
            if (m.getAnnotation(Property.class) != null) {
                pm.add(m);
            }
        }

        HashMap<String, Object[]> ret = new HashMap<String, Object[]>();
        
        for (Method m: pm) {
            Parameter[] params = m.getParameters();
            ArrayList<ArrayList<Object>> vals = new ArrayList<ArrayList<Object>>();
            for (Parameter p: params) {
                AnnotatedType a = p.getAnnotatedType();
                vals.add(helper(a, o, c));
            }
            int runs = 1;
            for (int i = 0; i < vals.size(); i++) {
                runs *= vals.get(i).size();
            }

            if (runs > 100) {
                runs = 100;
            }

            for (int i = 0; i < runs; i++) {
                Object[] test = new Object[vals.size()];
                int curr = 1;
                for (int j = 0; j < vals.size(); j++) {
                    if (j == vals.size() - 1) {
                        test[j] = vals.get(j).get(i/curr);
                    } else {
                        curr *= vals.get(j).size();
                        test[j] = vals.get(j).get(i % curr);
                    }
                }
                try {
                    if ((boolean) m.invoke(o, test)) {
                        ret.put(m.getName(), null);
                    } else {
                        ret.put(m.getName(), test);
                        break;
                    }
                } catch (IllegalAccessException | InvocationTargetException e){
                    ret.put(m.getName(), test);
                    break;
                }
            }
        }
        return ret;
    }

    public static ArrayList<Object> helper(AnnotatedType a, Object o, Class c) {
        ArrayList<Object> ret = new ArrayList<Object>();
        Annotation anno = a.getAnnotations()[0];
        if (anno.annotationType() == IntRange.class) {
            if (a.getType() != Integer.class) {
                throw new RuntimeException();
            }
            IntRange ai = (IntRange) anno;
            for (int i = ai.min(); i <= ai.max(); i++) {
                ret.add(i);
            }
        } else if (anno.annotationType() == StringSet.class) {
            if (a.getType() != String.class) {
                throw new RuntimeException();
            }
            StringSet as = (StringSet) anno;
            for (String s: as.strings()) {
                ret.add(s);
            }
        } else if (anno.annotationType() == ListLength.class) {
            ListLength al = (ListLength) anno;
            AnnotatedType inner = ((AnnotatedParameterizedType) a).getAnnotatedActualTypeArguments()[0];
            ArrayList<Object> list = helper(inner, o, c);
            for (int i = al.min(); i <= al.max(); i++) {
                if (i == 0) {
                    ret.add((List) new ArrayList());
                } else {
                    for (Object l: list) {
                        ArrayList<Object> temp = new ArrayList<Object>();
                        for (Object r: ret) {
                            List<Object> copy = new ArrayList<Object>((List<Object>) r);
                            if (copy.size() == i-1) {
                                copy.add(l);
                                temp.add(copy);
                            }
                        }
                        ret.addAll(temp);
                    }
                }
            }
        } else if (anno.annotationType() == ForAll.class) {
            if (a.getType() != Object.class) {
                throw new RuntimeException();
            }
            ForAll ao = (ForAll) anno;
            Method meth;
            try {
                meth = c.getDeclaredMethod(ao.name());
            } catch (NoSuchMethodException e) {
                throw new RuntimeException();
            }
            for (int i = 0; i < ao.times(); i++) {
                try {
                    ret.add(meth.invoke(o));
                } catch (IllegalAccessException | InvocationTargetException e){
                    throw new RuntimeException();
                }
            }
        } else {
            throw new RuntimeException();
        }
        return ret;
    }
}
