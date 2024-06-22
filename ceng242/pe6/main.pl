:- module(main, [is_blogpost_written_by/2, has_post_in_topic/2, get_follower_count_of_blogger/2, get_post_count_of_topic/2, filter_posts_by_date/4, recommend_posts/2, recommend_bloggers/2]).
:- [kb].

% DO NOT CHANGE THE UPPER CONTENT, WRITE YOUR CODE AFTER THIS LINE

is_blogpost_written_by(BloggerNick, ShortPostName) :-
    posted(BloggerNick, PostID),
    blogpost(PostID, ShortPostName, _, _).
    
has_post_in_topic(BloggerNick, Topic) :-
    posted(BloggerNick, PostID),
    blogpost(PostID, _, Topic, _).
    
get_follower_count_of_blogger(BloggerNick, FollowerCount) :-
    findall(Follower, follows(_, BloggerNick), Followers),
    length(Followers, FollowerCount).
    
get_post_count_of_topic(Topic, PostCount) :-
    findall(BlogPost, blogpost(_, _, Topic, _), BlogPosts),
    length(BlogPosts, PostCount).
    
filter_posts_by_date([], _, _, []).
filter_posts_by_date([PostID | Rest], OldestDate, NewestDate, [PostID | FilteredRest]) :-
    blogpost(PostID, _, _, Date),
    Date >= OldestDate,
    Date =< NewestDate,
    filter_posts_by_date(Rest, OldestDate, NewestDate, FilteredRest).
    
filter_posts_by_date([PostID | Rest], OldestDate, NewestDate, FilteredRest) :-
    blogpost(PostID, _, _, Date),
    (Date < OldestDate ; Date > NewestDate),
    filter_posts_by_date(Rest, OldestDate, NewestDate, FilteredRest).
    
recommend_posts(ReaderNick, ListOfRecommendedPosts) :-
    reader(ReaderNick, Topics),
    findall(PostID, (
        blogpost(PostID, _, Topic, _),
        member(Topic, Topics),
        \+ alreadyread(ReaderNick, PostID)
    ), ListOfRecommendedPosts).
    
recommend_bloggers(ReaderNick, ListOfRecommendedBloggers) :-
    reader(ReaderNick, Topics),
    findall(BloggerNick, (
        blogger(BloggerNick),
        posted(BloggerNick, PostID),
        blogpost(PostID, _, Topic, _),
        member(Topic, Topics),
        \+ follows(ReaderNick, BloggerNick)
    ), Bloggers),
    sort(Bloggers, ListOfRecommendedBloggers).