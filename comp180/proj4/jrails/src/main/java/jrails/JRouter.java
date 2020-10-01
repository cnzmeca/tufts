package jrails;

import java.util.*;
import java.lang.reflect.*;

public class JRouter {
    private HashMap<String, String> routes = new HashMap<String, String>();

    public void addRoute(String verb, String path, Class clazz, String method) {
        routes.put(verb+path, clazz.getName()+"#"+method);
    }

    // Returns "clazz#method" corresponding to verb+URN
    // Null if no such route
    public String getRoute(String verb, String path) {
        return routes.get(verb+path);
    }

    // Call the appropriate controller method and
    // return the result
    public Html route(String verb, String path, Map<String, String> params) {
        String val = getRoute(verb, path);
        if (val == null) {
            throw new UnsupportedOperationException();
        }
        String[] vals = val.split("#");
        try {
            Class c = Class.forName(vals[0]);       
            Method m = c.getMethod(vals[1], Map.class);
            return (Html)m.invoke(null, params); 
        } catch (Exception e) {
            throw new RuntimeException(e);
        }
    }
}
