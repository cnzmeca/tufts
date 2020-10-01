package jrails;

public class Html {
    private String s;

    public Html(){
        this.s = "";
    }
   
    private Html(String s){
        this.s = s;
    }
    
    public String toString() {
        return s;
    }

    public Html empty() {
        return new Html("");
    }

    public Html seq(Html h) {
        return new Html(s + h.s);
    }

    public Html br() {
        return new Html(s + "<br/>");
    }

    public Html t(Object o) {
        return new Html(s + o.toString());
    }

    public Html p(Html child) {
        return new Html(s + "<p>" + child.s + "</p>");
    }

    public Html div(Html child) {
        return new Html(s + "<div>" + child.s + "</div>");
    }

    public Html strong(Html child) {
        return new Html(s + "<strong>" + child.s + "</strong>");
    }

    public Html h1(Html child) {
        return new Html(s + "<h1>" + child.s + "</h1>");
    }

    public Html tr(Html child) {
        return new Html(s + "<tr>" + child.s + "</tr>");
    }

    public Html th(Html child) {
        return new Html(s + "<th>" + child.s + "</th>");
    }

    public Html td(Html child) {
        return new Html(s + "<td>" + child.s + "</td>");
    }

    public Html table(Html child) {
        return new Html(s + "<table>" + child.s + "</table>");
    }

    public Html thead(Html child) {
        return new Html(s + "<thead>" + child.s + "</thead>");
    }

    public Html tbody(Html child) {
        return new Html(s + "<tbody>" + child.s + "</tbody>");
    }

    public Html textarea(String name, Html child) {
        return new Html(s + "<textarea name=\"" + name + "\">" + child.s + "</textarea>");
    }

    public Html link_to(String text, String url) {
        return new Html(s + "<a href=\"" + url + "\">" + text + "</a>");
    }

    public Html form(String action, Html child) {
        return new Html(s + "<form action=\"" + action + "\" accept-charset=\"UTF-8\" method=\"post\">" + child.s + "</form>");
    }

    public Html submit(String value) {
        return new Html(s + "<input type=\"submit\" value=\"" + value + "\"/>");
    }
}
