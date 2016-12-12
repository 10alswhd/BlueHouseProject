let httpPipeline = ConnectionPipeline()
httpPipeline.addPipeline(ResponseHeaderPipeline.self)
httpPipeline.addPipeline(URLParamParser.self)


let routes = Router()

routes.add(.Get, path: "/par/value") { (connection) -> Connection in
    //return Connection(request: connection.request)
    return httpPipeline.respond(BaseController().index(connection))
}

routes.add(.Get, path: "/value") { (connection) -> Connection in
  let bc = BaseController(pipeline: httpPipeline)
  return bc.index(connection)
}

routes.add(.Get, path: "/struct") { (connection) -> Connection in
  return StructResponse().index(connection)
}

routes.add(.Get, path: "/base") { (connection) -> Connection in
    return BaseController().index(connection)
}
