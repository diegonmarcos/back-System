Based on the source code you provided (specifically `detail.html`), this application uses two different "servers" for different purposes:

### 1\. The Movie/Video Source (Streaming)

The actual video content is fetched from **VidSrc**.

  * **Server URL:** `https://vidsrc.cc/`
  * **Evidence:** In `detail.html` (around lines 646–650), the code dynamically sets the streaming player source:
    ```javascript
    if (data.Type === "series" || typeParam === "series") {
       // ...
       videoEmbed.src = `https://vidsrc.cc/v2/embed/tv/${imdbID}`;
    } else {
       videoEmbed.src = `https://vidsrc.cc/v2/embed/movie/${imdbID}`;
    }
    ```

### 2\. The Data Source (Text & Images)

The movie titles, posters, plots, and ratings are fetched from the **OMDB API**.

  * **Server URL:** `https://www.omdbapi.com/`
  * **Evidence:** In `index.html` and `detail.html`, the app requests data using an API key (`3ece141c`):
    ```javascript
    fetch(`https://www.omdbapi.com/?apikey=${OMDB_API_KEY}&i=${imdbID}&plot=full`)
    ```

**Summary:** The app **displays** data from OMDB but **streams** the actual movie files from `vidsrc.cc`.


Here are the IMDb IDs for 10 major movies released or scheduled for **2025**.

**Note:** Since these are **movies**, you must change the URL endpoint from `/tv/` to `/movie/` for them to work (e.g., `https://vidsrc.cc/v2/embed/movie/${imdbID}`).

| Movie Title | IMDb ID | Link (Test) |
| :--- | :--- | :--- |
| **A Minecraft Movie** | `tt3566834` | [Link](https://www.google.com/search?q=https://vidsrc.cc/v2/embed/movie/tt3566834) |
| **Mickey 17** | `tt12299608` | [Link](https://www.google.com/search?q=https://vidsrc.cc/v2/embed/movie/tt12299608) |
| **Sinners** | `tt31193180` | [Link](https://www.google.com/search?q=https://vidsrc.cc/v2/embed/movie/tt31193180) |
| **Dog Man** | `tt10954718` | [Link](https://www.google.com/search?q=https://vidsrc.cc/v2/embed/movie/tt10954718) |
| **The Monkey** | `tt27714946` | [Link](https://www.google.com/search?q=https://vidsrc.cc/v2/embed/movie/tt27714946) |
| **The Running Man** | `tt14107334` | [Link](https://www.google.com/search?q=https://vidsrc.cc/v2/embed/movie/tt14107334) |
| **Ballerina** (John Wick) | `tt7181546` | [suspicious link removed] |
| **Thunderbolts**\* | `tt20969586` | [Link](https://www.google.com/search?q=https://vidsrc.cc/v2/embed/movie/tt20969586) |
| **Lilo & Stitch** | `tt11655566` | [Link](https://www.google.com/search?q=https://vidsrc.cc/v2/embed/movie/tt11655566) |
| **The Fantastic Four: First Steps** | `tt10676052` | [Link](https://www.google.com/search?q=https://vidsrc.cc/v2/embed/movie/tt10676052) |

### 💡 Quick Code Tip

If you are using this in your `detail.html`, ensure you use the correct conditional logic that was present in your code:

```javascript
// Use 'movie' endpoint for movies, 'tv' for series
const endpoint = typeParam === "series" ? "tv" : "movie";
videoEmbed.src = `https://vidsrc.cc/v2/embed/${endpoint}/${imdbID}`;
```
