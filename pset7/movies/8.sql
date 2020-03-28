SELECT people.name
FROM people, movies
JOIN stars ON people.id = stars.person_id
AND stars.movie_id = movies.id
WHERE movies.title = "Toy Story";