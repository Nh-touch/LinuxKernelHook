import os
import re
import json
import fileinput

class AnalysisManager(object):
    NODE_BEGIN  = "considering target"
    NODE_END    = "finished prerequisites of target"
    CMD_BEGIN   = "must remake"
    CMD_END_Y   = "successfully remade"
    CMD_END_N   = "no need to remake"

    def __init__(self):
        self.__raw_content = None
        self.__nodes = {}
        self.__relations = {}
        self.__id = 0

    def __read_content(self, path):
        pass

    def do_analysis(self, content):
        node_parent_id = -1

        nodes_history = []
        nodes_parents_map = {}
        nodes_relpath_map = {}
        cmd_target = None
        for line in content:
            lower_content = line.strip().lower()

            # cmd begin
            if lower_content.startswith(AnalysisManager.CMD_END_Y) or lower_content.startswith(AnalysisManager.CMD_END_N):
                cmd_target = None
                continue

            if cmd_target:
                id = nodes_relpath_map[cmd_target]
                self.__nodes[str(id)]['cmd'].append(line)
                continue

            # node begin
            if lower_content.startswith(AnalysisManager.NODE_BEGIN):
                # get target relpath content
                p = re.compile("(?<= ').*(?='.)")
                relpath = re.findall(p, line)[0]

                if not os.path.exists(relpath):
                    print('not exists', relpath)

                # generate id
                if not relpath in nodes_relpath_map:
                    node_id = self.__id
                    self.__id += 1
                    nodes_relpath_map[relpath]= node_id
                else:
                    node_id = nodes_relpath_map[relpath]


                # refresh relations
                if node_parent_id >= 0:
                    if not str(node_parent_id) in self.__relations:
                        self.__relations[str(node_parent_id)] = []

                    if not str(node_id) in self.__relations[str(node_parent_id)]:
                        self.__relations[str(node_parent_id)].append(str(node_id))

                # append to parent
                nodes_parents_map[node_id] = node_parent_id
                node_parent_id = node_id

                self.__add_one_node(node_id, relpath.strip(), [])
                # recording
                nodes_history.append((node_id, relpath))
                continue

            # node end
            if lower_content.startswith(AnalysisManager.NODE_END):
                # record node info
                node_id, relpath = nodes_history.pop()


                p = re.compile("(?<= ').*(?='.)")
                relpath_new = re.findall(p, line)[0]

                if relpath_new != relpath:
                    print("!!!!!!!!!!!!!!!!!!!!!!!!!! new old", relpath_new, relpath)

                # recover parent id
                node_parent_id = nodes_parents_map[node_id]
                continue

            # cmd begin
            if lower_content.startswith(AnalysisManager.CMD_BEGIN):
                p = re.compile("(?<= ').*(?='.)")
                target = re.findall(p, line)[0]
                cmd_target = target
                continue


        print(self.__nodes)
        print(self.__relations)

    def __get_leaf_nodes(self):
        pass

    def __get_implicit_depends(self):
        pass

    # todo
    def __add_one_node(self, node_id, path, cmds):
        data            = {}
        data['relpath'] = path
        data['cmd']     = cmds

        self.__nodes[str(node_id)] = data

if __name__ == "__main__":
    analysis_manager = AnalysisManager()
    with fileinput.input() as f_input:
        analysis_manager.do_analysis(f_input)


