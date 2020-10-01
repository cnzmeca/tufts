# House All Tufts Students (HATS)
###### Team 20 (Michael Morscher, Eric Tolhurst, Zhaoying Xu, Christian Zinck)
### Problem Statement
- Finding off campus housing around Tufts’ campus is very difficult. There are many sites with only particular information, and the options are impossible to visualize.
### Our Solution
- A web application that takes in user preferences and presents a visual display of the top three recommended potential off-campus houses by integrating data from multiple sources, and displaying relevant market information as well.
	- The user preferences will be: preferred location to be closest to (eg. Halligan), distance willing to travel, and target rent amount. Each will be entered using sliders representing the importance of each metric.
	- Along with top three options, charts will be displayed showing average rent and other details in target area.
### User Scenario
- *A desperate Tufts student opens up the website. An entry page will be available for them to enter relevant preferences for off-campus housing. Once submitted, the page redirects to a Google map of Tufts campus, centered on target location, with top 3 housing options displayed on the map. Clicking on the houses or a “display options” button will allow them to view housing information in readable format on a pop-up/float chart. Student can share the results with self or friends.*
### Features to Implement (Including "Pick 3")
- Front-End Framework (React)
- Reporting with Chart and Graphs: pop-up chart containing detailed description of best houses selected for the user
- Email/SMS to share the compiled housing list to self or friends
- Google Maps API
### Data Used
- Coordinates of houses for rent (APIs)
- Local housing market data (APIs)
- User preferences (Client-supplied)
	- Location
	- Distance
	- Price range
### Algorithms / Techniques
- We will write a custom algorithm to determine the best housing options, weighted by how the user prioritizes location, price, quality, distance from target location, etc. Essentially, we will find the closest matches by comparing all options and calculating the percent differences of the actual conditions from the preferred conditions. From this, a "composite score" will be calculated to sort the matches.
	- Multiple data sources will be integrated to pull data for these factors as appropriate. Planned sources based on initial research listed in *APIs* section below.
### APIs 
- Google Maps
- Multiple housing information APIs (potentially including Zillow and Walk Score)
### Wireframes
![alt text](https://github.com/tuftsdev/comp20-f2017-team20/blob/master/20_Wireframes.png "Team 20 Wireframe")

## Comments by Ming
* Using React is not a feature
* Ask Josie Barth about her experience using Zillow. :-). Josie is a senior.
