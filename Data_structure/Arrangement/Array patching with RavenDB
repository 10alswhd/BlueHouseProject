using (var store = NewDocumentStore())
{
    using (var s = store.OpenSession())
    {
        s.Store(new Post
            {
                //Create an empty list that we can add items to later
                Comments = new List<Comment>()									
            });
	s.SaveChanges();
    }

    store.DatabaseCommands.Batch(
        new[] {
            new PatchCommandData
                {
                    Key = "posts/1",
                    Patches = new[]
                    {
                        new PatchRequest
                            {
                                Type = PatchCommandType.Add,
                                Name = "Comments",
                                Value = RavenJObject.FromObject(new Comment {AuthorId = "authors/456"})
                            },
                        new PatchRequest
                            {
                                Type = PatchCommandType.Add,
                                Name = "Comments",
                                Value = RavenJObject.FromObject(new Comment {AuthorId = "authors/789"})
                            },
                        new PatchRequest
                            {
                                Type = PatchCommandType.Add,
                                Name = "Comments",
                                Value = RavenJObject.FromObject(new Comment {AuthorId = "authors/101112"})
                            },
                    }
                }
            });

    using (var s = store.OpenSession())
    {
        var comments = s.Load<Post>("posts/1").Comments;
        Assert.Equal(3, comments.Count);
        Assert.Equal("authors/456", comments[0].AuthorId);
        Assert.Equal("authors/789", comments[1].AuthorId);
        Assert.Equal("authors/101112", comments[2].AuthorId);
    }
}
